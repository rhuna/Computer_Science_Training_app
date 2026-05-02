const { solve } = require('./main');
if (!solve().includes('PASS_BASE_CONVERTER')) throw new Error('Expected token missing');
console.log('PASS_BASE_CONVERTER');
