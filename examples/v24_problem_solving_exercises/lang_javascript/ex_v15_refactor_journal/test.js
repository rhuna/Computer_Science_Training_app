const { execSync } = require("child_process");
const output = execSync("node main.js").toString();
if (!output.includes("PASS_V15_REFACTOR_JOURNAL")) throw new Error("Expected token missing");
console.log("JS_TEST_PASS");
