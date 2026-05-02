const fs=require("fs"); const n=parseInt((fs.readFileSync(0,"utf8").trim()||"42").split(/\s+/)[0],10); console.log(n.toString(2)); console.log(n.toString(16).toUpperCase());
