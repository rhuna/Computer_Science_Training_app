declare const require: any;
const fs=require("fs"); const l=fs.readFileSync(0,"utf8").split(/\r?\n/); const age=parseInt(l[0]||"0",10); const email=l[1]||""; const user=l[2]||""; console.log(age>=18 && email.includes("@") && user.length>=3 ? "valid" : "invalid");
