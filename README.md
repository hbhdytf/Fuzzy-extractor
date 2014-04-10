# main:  选择最佳虹膜特征码，并将其图像数据段切分

## 支持特性
 - 虹膜特征切分和恢复的操作
 - Fuzzy Extractor 的实现程序
 - 产生密钥的基本操作

## Hamming distance

The Hamming distance between two strings of the same length is the minimum number of substitutions required to transform one into the other.

Let u and v be strings of length n, then the Hamming distance d(u,v) = card({ i | u<sub>i</sub> ≠ v<sub>i</sub> })

## Levenshtein distance

The Levenshtein distance between two strings (not necessarily the same length) is the minimum number of additions, substitutions and deletions required to transform one into another.

The most straightforward way to derive the formula for Levenshtein distance is using recursion.

Let u=u<sub>1</sub>u<sub>2</sub>...u<sub>m</sub>, v=v<sub>1</sub>v<sub>2</sub>...v<sub>n</sub>, we wish to find the formula for the Levenshtein distance d(u,v)

 1. If min(m,n) = 0, then max(len(m), len(n)). (This is obvious, since if one string is empty, then the distance is just the number of additions to get from the empty string to the non-empty string)
 - If the last two characters are the same, that is: u<sub>m</sub> = v<sub>n</sub>, then d(u,v)=d(u<sub>1</sub>u<sub>2</sub>...u<sub>m-1</sub>, v<sub>1</sub>v<sub>2</sub>...v<sub>n-1</sub>)
 - Otherwise, there are three options left to check, compute them all and pick the minimum:
   - Delete u<sub>m</sub> and recurse
   - Delete v<sub>n</sub> and recurse or
   - Delete both and recurse
  
Why does this last case work?

By the last case, we know that both strings are non-empty, and that their last characters differ. This means that we can delete the last character of one or the other or both, counting the deletion as one, and recurse until either of the first two cases are met.

To see this in action, suppose we are testing "solve" and "resolve", we know that we can append two characters to the former to get the latter. Using our algorithm, we know that they are both non-empty, and we will hit case 2 exactly five times, at which point we test "" and "re", which case 1 returns a distance of 2.

