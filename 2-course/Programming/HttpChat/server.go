package main

import (
	"bufio"
	"fmt"
	"io"
	"log"
	"net"
	"os"
	"strings"
	"strconv"
	"time"
)


type Client struct {
	conn 	net.Conn
	name 	string
	friend 	string
	ch 		chan string
	RSAn    int64
	RSAkey  int64
}


type Message struct {
	client Client
	msg  string
}


func NewMessage(client Client, msg string) (m Message) {
	m.client = client
	m.msg = msg
	return
}


func main() {
	ln, err := net.Listen("tcp", ":6000")
	if err != nil {
		fmt.Println(err)
		os.Exit(1)	
	}
	
	msgchan := make(chan Message, 1)
	addchan := make(chan Client, 1)
	rmchan  := make(chan Client, 1) // remove
	
	go handleMessages(msgchan, addchan, rmchan)

	for {
		conn, err := ln.Accept()
		if err != nil {
			fmt.Println(err)
			continue	
		}
		go handleConnection(conn, msgchan, addchan, rmchan)
	}
	
}


func (c Client) ReadLinesInto(ch chan<- Message) {
	bufc := bufio.NewReader(c.conn)
	for {
		line, err := bufc.ReadString('\n')
		if err != nil {
			return	
		}	
		ch <- NewMessage(c, line)
	}
	return
}


func (c Client) WriteLinesFrom(ch <-chan string) {
	for {
		select {
		case msg := <-ch:
			_, err := io.WriteString(c.conn, msg)
			if err != nil {
				return	
			}	
		}
	}
	return
}

func handleConnection(c net.Conn, 
					  msgchan chan<- Message, 
					  addchan chan<- Client, 
					  rmchan  chan<- Client) {
	defer c.Close()
	
	var client Client
	client.conn = c
	client.ch = make(chan string, 1)


	line, err := bufio.NewReader(client.conn).ReadString('\n')
	line = strings.TrimSpace(line)
	log.Printf(line)
	arr := strings.Split(line, " ")
	if err == nil && len(arr) == 5 && arr[0] == "connect" {
		n,   err1 := strconv.ParseInt(arr[3], 10, 64)
		key, err2 := strconv.ParseInt(arr[4], 10, 64)
		if err1 == nil && err2 == nil {
			client.name = arr[1]
			client.friend = arr[2]
			client.RSAn = int64(n)
			client.RSAkey = int64(key)
		} else {
			fmt.Print(err1)
			fmt.Print(err2)
			return
		}
	} else {
		return
	}

	time.Sleep(time.Second * 1)
	addchan <- client
	defer func(){
		rmchan <- client
	}()

	// I/O	
	go client.WriteLinesFrom(client.ch)
	client.ReadLinesInto(msgchan)

}


func handleMessages(msgchan <-chan Message, addchan <-chan Client, rmchan <-chan Client) {
	clients := make(map[string]Client)

	for {
		select {
			case Mssg := <-msgchan:
				log.Printf("New message: %s", Mssg.msg)
				arr := strings.Split(Mssg.msg, " ")
				if len(arr) > 2 && arr[0] == "text"{
					sender   := Mssg.client.name
					receiver := Mssg.client.friend
					if reciev, ok := clients[receiver]; ok && reciev.friend == sender {
						Mssg.client.ch <- Mssg.msg
						reciev.ch <- Mssg.msg
					}
				}

			case client := <-addchan:
				if _, ok := clients[client.name]; !ok {
					log.Printf("New client: %v; nick: %s\n", 
						       client.conn.RemoteAddr(), 
						       client.name)
					clients[client.name] = client

					if val2, ok2 := clients[client.friend]; ok2 {
						client.ch <- fmt.Sprintf("decode %d %d\n", 
							                     val2.RSAn, 
							                     val2.RSAkey)	
						val2.ch   <- fmt.Sprintf("decode %d %d\n", 
							                     client.RSAn, 
							                     client.RSAkey)
						log.Printf("SEND to BOTH decode")
					}
				}

			case client := <-rmchan:
				log.Printf("Client disconnects: %v; nick: %s\n", 
					       client.conn.RemoteAddr(), client.name)
				delete(clients, client.name)
		}	
	}
	
}
