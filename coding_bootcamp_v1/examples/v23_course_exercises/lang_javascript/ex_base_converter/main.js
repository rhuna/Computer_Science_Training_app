const fs = require('fs');
const raw = fs.readFileSync(0, 'utf8').trim();
const n = raw ? Number(raw) : 42;
console.log('binary', n.toString(2));
console.log('hex', n.toString(16).toUpperCase());
