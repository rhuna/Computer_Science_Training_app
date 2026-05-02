package main

import (
    "fmt"
    "strings"
)

func main() {
    text := "go word frequency starter"
    counts := map[string]int{}
    for _, word := range strings.Fields(text) {
        counts[word]++
    }
    for word, count := range counts {
        fmt.Printf("%s: %d\n", word, count)
    }
}
