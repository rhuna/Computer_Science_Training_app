fun main() {
    val text = "kotlin word frequency starter"
    val counts = mutableMapOf<String, Int>()
    for (word in text.split(Regex("\\s+"))) {
        counts[word] = (counts[word] ?: 0) + 1
    }
    for ((word, count) in counts) {
        println("$word: $count")
    }
}
