const firebase = require("firebase/app")
const firestore = require("firebase/firestore");

const firebaseConfig = {
  apiKey: "AIzaSyCEIIZYTV-hSUG0rc3LlOWWrCjjibOguUQ",
  authDomain: "ammonia-detection.firebaseapp.com",
  databaseURL: "https://ammonia-detection-default-rtdb.asia-southeast1.firebasedatabase.app",
  projectId: "ammonia-detection",
  storageBucket: "ammonia-detection.appspot.com",
  messagingSenderId: "797230843227",
  appId: "1:797230843227:web:c0fe26a2a3892b5bf0067e",
  measurementId: "G-ER4YL3CNSE"
};

const app = firebase.initializeApp(firebaseConfig)
const database = firestore.getFirestore(app)
let date = new Date()

function adddata(val){
    const year = date.getFullYear()
    const month = date.getMonth() + 1
    const day = date.getDate()
    const hours = date.getHours()
    const minutes = date.getMinutes()
    const seconds = date.getSeconds()
    const data = {
        record_date : {day,month,year},
        time : {hours,minutes,seconds},
        avg_ppm : val
    }
    firestore.addDoc(firestore.collection(database , "ammonia_level_history") , data)
}
module.exports = {
    adddata
}