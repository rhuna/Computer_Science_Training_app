use std::collections::BTreeMap;

fn main() {
    let text = "rust word frequency starter";
    let mut counts: BTreeMap<&str, i32> = BTreeMap::new();
    for word in text.split_whitespace() {
        *counts.entry(word).or_insert(0) += 1;
    }
    for (word, count) in counts {
        println!("{}: {}", word, count);
    }
}
