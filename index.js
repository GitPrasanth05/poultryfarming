const axios = require("axios");
const {adddata} = require("./firestore")
const readfromrealtimedatabase = require("./input-realtime-db");
const url1 = "http://localhost:8000/data";
const express = require("express");
const cors = require("cors");
const app = express();

app.use(express.json());
app.use(cors());

let array = []
let sum = 0

async function senddata(){
    const data = await readfromrealtimedatabase();
    try { 
        const response1 = await axios.post(url1, data);
        console.log("Response Received from url1:", response1.data);
    } catch (error) {
        console.log("Error sending data to url1:", error);
    }

    const ppmValue = data && data.value
    array.push(ppmValue)
    sum += ppmValue
    if(array.length >= 10){
        adddata(sum/10)
        array.length = 0
        sum = 0
    }
}  
setInterval(senddata, 2000)
