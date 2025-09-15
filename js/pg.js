import { initializeApp } from "https://www.gstatic.com/firebasejs/9.18.0/firebase-app.js";
import { getDatabase, ref, onValue } from "https://www.gstatic.com/firebasejs/9.18.0/firebase-database.js";

const firebaseConfig = {
  apiKey: "AIzaSyAKxGq25Wal0ywZY0oTAgmbuyRvtWfwSfo",
  authDomain: "atvdsensordht22.firebaseapp.com",
  databaseURL: "https://atvdsensordht22-default-rtdb.firebaseio.com",
  projectId: "atvdsensordht22",
  storageBucket: "atvdsensordht22.appspot.com",
  messagingSenderId: "SENDER_ID",
  appId: "APP_ID"
};

const app = initializeApp(firebaseConfig);
const db = getDatabase(app);

const tempEl = document.getElementById("temp");
const humEl = document.getElementById("hum");

const tempRef = ref(db, "/sensores/dht22/temperatura");
const humRef = ref(db, "/sensores/dht22/umidade");

onValue(tempRef, (snapshot) => {
  tempEl.textContent = snapshot.val() ?? "--";
});

onValue(humRef, (snapshot) => {
  humEl.textContent = snapshot.val() ?? "--";
});
