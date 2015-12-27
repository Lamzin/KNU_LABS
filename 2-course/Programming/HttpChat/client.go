package main

import "net"
import "fmt"
import "bufio"
import "os"
import "time"
import "strings"
import "strconv"
import "./rsa"
import "math/rand"

func main() {
	rand.Seed(time.Now().UTC().UnixNano())

	var dial dialog
	dial.is_exist = false
	dial.RSAdecode = rsa.NewRSA()
	dial.friend1, _ = bufio.NewReader(os.Stdin).ReadString('\n')
	dial.friend2, _ = bufio.NewReader(os.Stdin).ReadString('\n')

	dial.friend1 = strings.TrimSpace(dial.friend1)
	dial.friend2 = strings.TrimSpace(dial.friend2)

	conn, err := net.Dial("tcp", "127.0.0.1:6000")
	if err != nil {
		fmt.Print("Here!")
		fmt.Print(err)	
		return
	}
	
	dial.conn = conn
	dial.handleConnection()

}


type dialog struct {
	conn net.Conn
	friend1 string
	friend2 string
	RSAdecode rsa.RSA
	RSAencode rsa.RSA
	keyDecode int
	keyEncode int
	is_exist bool
}


func (d *dialog) sendMessage() {
	fmt.Fprintf(d.conn, "connect %s %s %d %d\n", 
				d.friend1, 
				d.friend2, 
				d.RSAdecode.Numb, 
				d.RSAdecode.DecodeExp)

	reader := bufio.NewReader(os.Stdin)
	for {
		text, err := reader.ReadString('\n')
		if err != nil {
			fmt.Print(err)
			return
		}

		if !d.is_exist {
			fmt.Printf("Wait your friend...")
			continue
		}

		key := rand.Intn(128)
		fmt.Fprintf(d.conn, "text %d %s\n", d.RSAencode.Decode(int64(key)), DecodeText(text, key))
	}
}


func (d *dialog) receiveMessage() {
	for {
		// fmt.Print(d.RSAdecode.Numb, d.RSAdecode.DecodeExp, d.RSAdecode.EncodeExp, "\n")
		// fmt.Print(d.RSAencode.Numb, d.RSAencode.DecodeExp, d.RSAencode.EncodeExp, "\n")

		msg, err := bufio.NewReader(d.conn).ReadString('\n')
		if err != nil {
			fmt.Print(err)
			return
		}			
		
		msg = strings.TrimSpace(msg)
		arr := strings.Split(msg, " ")

		if len(arr) > 2 {
			switch arr[0] {
			case "decode":
				if len(arr) == 3 {
					n, err1 := strconv.ParseInt(arr[1], 10, 64); 
					key, err2 := strconv.ParseInt(arr[2], 10, 64)
					if err1 == nil && err2 == nil {
							d.is_exist = true
							d.RSAencode.Numb = int64(n)
							d.RSAencode.DecodeExp = int64(key)
					}
				}
			case "text":
				if key, err := strconv.ParseInt(arr[1], 10, 64); err == nil {				
					text := strings.Join(arr[2:], " ")
					text = EncodeText(text, int(d.RSAdecode.Encode(int64(key))))
					fmt.Printf("Friend: %s\n", text)
				}
			}
		} 

	}
}


func (d *dialog) handleConnection() {
	go d.receiveMessage()
	d.sendMessage()
}


func DecodeText(s string, key int) string {
	arr := []byte(s)
	for i := 0; i < len(arr); i++ {
		arr[i] ^= byte(key)
	}
	return string(arr)
}


func EncodeText(s string, key int) string {
	arr := []byte(s)
	for i := 0; i < len(arr); i++ {
		arr[i] ^= byte(key)
	}
	return string(arr)
}
