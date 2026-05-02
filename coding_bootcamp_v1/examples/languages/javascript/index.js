const text = process.argv.slice(2).join(' ') || 'javascript word frequency starter';
const counts = new Map();
for (const word of text.split(/\s+/)) {
  counts.set(word, (counts.get(word) || 0) + 1);
}
for (const [word, count] of counts) {
  console.log(`${word}: ${count}`);
}
