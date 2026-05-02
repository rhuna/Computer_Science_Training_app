const { execSync } = require("child_process");
const output = execSync("node main.js").toString();
if (!output.includes("PASS_SYSTEM_DESIGN_PROMPT")) throw new Error("Expected token missing");
console.log("JS_TEST_PASS");
