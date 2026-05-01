const { solve } = require('./main');
if (!solve().includes('PASS_WORD_FREQUENCY')) throw new Error('Expected PASS_WORD_FREQUENCY');
console.log('PASS_WORD_FREQUENCY');
