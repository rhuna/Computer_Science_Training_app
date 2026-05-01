function solve(text = 'apple apple banana') {
  const counts = {};
  for (const word of text.toLowerCase().split(/\s+/)) counts[word] = (counts[word] || 0) + 1;
  return counts.apple === 2 && counts.banana === 1 ? 'PASS_WORD_FREQUENCY' : 'FAIL_WORD_FREQUENCY';
}
console.log(solve());
module.exports = { solve };
