const express = require("express");
const cors = require("cors");
const app = express();

app.use(express.json());
app.use(cors());

let data1 = null;
app.post("/data", (req, res) => {
  data1 = req.body;
  res.send("successful");
  console.log("Data1 Received:", data1);
});

app.get("/getServerData", (req, res) => {
  const ppmValue = data1 && data1.value;
  console.log("Sending data:", ppmValue);
  if (!ppmValue) {
    res.send("NIL");
  } else {
    res.send(ppmValue.toString());
  }
});
app.listen(8000, () => {
  console.log("Running on 8000 port");
});
