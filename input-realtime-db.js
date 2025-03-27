const admin = require('firebase-admin');
const serviceAccount = require('./ammonia-detection-firebase-adminsdk-yxdum-29160f5363.json');

admin.initializeApp({
credential: admin.credential.cert(serviceAccount),
databaseURL: 'https://ammonia-detection-default-rtdb.asia-southeast1.firebasedatabase.app/' 
});

const db = admin.database();
const location = db.ref("ammoniaValues");

function readfromrealtimedatabase() {
    return new Promise((resolve, reject) => {
        location.once("value")
        .then((snapshot) => {
            resolve(snapshot.val());
            return snapshot.val()
        })
        .catch((error) => {
            reject(error);
        });
    });
}

module.exports = readfromrealtimedatabase;