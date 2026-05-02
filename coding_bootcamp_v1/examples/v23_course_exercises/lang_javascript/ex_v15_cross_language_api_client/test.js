const { execSync } = require("child_process");
const output = execSync("node main.js").toString();
if (!output.includes("PASS_V15_CROSS_LANGUAGE_API_CLIENT")) throw new Error("Expected token missing");
console.log("JS_TEST_PASS");
