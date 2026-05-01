const { execSync } = require("child_process");
const output = execSync("node main.js").toString();
if (!output.includes("PASS_ROLE_AI_EVAL")) throw new Error("Expected token missing");
console.log("JS_TEST_PASS");
