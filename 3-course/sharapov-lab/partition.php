// algorithm details here:
// https://docs.google.com/document/d/16u5-Nbm6LQEZbxvpHM80o6hlP6EtAGWl2nS5qCHlfvs/edit?usp=sharing

<?php
class Foo {
    function main($index, $n) {
        $combinations = $this->getAllSumCombinations($n);
        $enough = false;
        $skipped = "0";
        $combination = $combinations[0];
        for ($i = 0; $i < count($combinations); $i++) {
            $c = $this->getPartitionCountInBlock($combinations[$i]);
            if (bccomp(bcadd($skipped, $c), $index) >= 0) {
                $combination = $combinations[$i];
                $enough = true;
                break;
            }
            $skipped = bcadd($skipped, $c);
        }
        if (!$enough) {
            return "fatal: index too big";
        }
        $used = array();
        $used_count = "0";
        for ($i = 0; $i < $n; $i++) {
            array_push($used, "-1");
        }
        $index = bcsub($index, $skipped);
        $skipped = "0";
        $set_index = "0";
        while ($used_count < $n) {
            for ($j = 0; $j < count($combination); $j++) {
                if ($j > 0 && $combination[$j - 1] == $combination[$j]) {
                    continue;
                }
                $tmp_combination = $combination;
                unset($tmp_combination[$j]);
                $tmp_combination = array_values($tmp_combination);
                $x = $this->getPartitionCountInBlock($tmp_combination);
                $c = $this->getCombinations(bcsub($combination[$j], "1"), bcsub(bcsub($n, $used_count), "1"));
                if (bccomp(bcadd($skipped, bcmul($c, $x)), $index) < 0) {
                    $skipped = bcadd($skipped, bcmul($c, $x));
                } else {
                    $combination_number = bcadd(bcdiv(bcsub(bcsub($index, $skipped), "1"), $x), "1");
                    $set_combination = $this->getCombinationByIndex($combination_number, bcsub($combination[$j], "1"), bcsub(bcsub($n, $used_count), "1"));
                    $set_combination = array_merge(array(0), $set_combination);
                    for ($ii = 0, $jj = 0, $not_used_index = 0; $ii < $n && $jj < count($set_combination); $ii++) {
                        if ($used[$ii] == -1) {
                            if ($not_used_index == $set_combination[$jj]) {
                                $used[$ii] = $set_index;
                                $jj++;
                            }
                            $not_used_index++;
                        }
                    }
                    $used_count = bcadd($used_count, $combination[$j]);
                    unset($combination[$j]);
                    $combination = array_values($combination);
                    $skipped = bcadd($skipped, bcmul(bcsub($combination_number, "1"), $x));
                    $set_index++;
                    break;
                }
            }
        }
//        echo join(', ', $used), "\r\n";
        $map = array();
        for ($i = 0; $i < count($used); $i++) {
            $map[$used[$i]] = array();
        }
        for ($i = 0; $i < count($used); $i++) {
            array_push($map[$used[$i]], $i + 1);
        }
        $sarr = array();
        for ($i = 0; $i < count($map); $i++) {
            array_push($sarr, join(', ', $map[$i]));
        }
        return '{'.join('}, {', $sarr).'}';
    }
    function getPartitionCountInBlock($combination) {
        $n = 0;
        for ($i = 0; $i < count($combination); $i++) {
            $n += $combination[$i];
        }
        $count = "1";
        for ($j = 0; $j < count($combination); $j++) {
            $count = bcmul($count, $this->getCombinations($combination[$j], $n));
            $n -= $combination[$j];
        }
        $l = 1;
        for ($j = 1; $j < count($combination); $j++) {
            if ($combination[$j - 1] == $combination[$j]) {
                $l++;
            } else {
                $count = bcdiv($count, $this->getFactorial($l));
                $l = 1;
            }
        }
        $count = bcdiv($count, $this->getFactorial($l));
        return $count;
    }
    function getAllSumCombinations($n) {
        $combinations = array();
        for ($combinationSize = $n; $combinationSize > 0; $combinationSize--) {
            $currentCombination = array();
            for ($i = 0; $i + 1 < $combinationSize; $i++) {
                array_push($currentCombination, 1);
            }
            array_push($currentCombination, $n - $combinationSize + 1);
            array_push($combinations, $currentCombination);
            for ($haveNext = true; $haveNext;) {
                $haveNext = false;
                $suffixSum = 0;
                for ($i = $combinationSize - 1; $i > 0; $i--) {
                    $suffixSum += $currentCombination[$i];
                    if ($currentCombination[$i - 1] + $suffixSum >= ($currentCombination[$i - 1] + 1) * ($combinationSize - $i + 1))
                    {
                        $currentCombination[$i - 1] += 1;
                        $suffixSum--;
                        for ($j = $i; $j < $combinationSize; $j++) {
                            $currentCombination[$j] = $currentCombination[$i - 1];
                            $suffixSum -= $currentCombination[$i - 1];
                        }
                        $currentCombination[$combinationSize - 1] += $suffixSum;
                        array_push($combinations, $currentCombination);
                        $haveNext = true;
                        break;
                    }
                }
            }
        }
        return $combinations;
    }
    function getCombinationByIndex($index, $k, $n) {
        $combination = array();
        $skipped = gmp_init(0);
        for ($i = 1; count($combination) < $k; $i++) {
            $c = $this->getCombinations($k - 1 - count($combination), $n - $i);
            if (gmp_cmp(gmp_add($skipped, $c), gmp_init($index)) >= 0) {
                array_push($combination, $i);
            } else {
                $skipped = gmp_add($skipped, $c);
            }
        }
        return $combination;
    }
    function getCombinations($k, $n) {
        $c = $this->getFactorial($n);
        $c = gmp_div($c, $this->getFactorial($k));
        $c = gmp_div($c, $this->getFactorial($n - $k));
        return $c;
    }
    function getFactorial($n) {
        $fact = "1";
        for ($i = 1; $i <= $n; $i++) {
            $fact = bcmul($fact, (string) $i);
        }
        return $fact;
    }
}
$foo = new Foo;
echo $foo->main("203", "100");
?>
