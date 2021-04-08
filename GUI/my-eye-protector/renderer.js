const myNotification = new Notification('Open the DM', {
  body: 'DM app has been open.'
})

myNotification.onclick = () => {
  console.log('Notification clicked')
}


////////// Online / Offline Event Detection
// const alertOnlineStatus = () => { window.alert(navigator.onLine ? 'online' : 'offline') }

// window.addEventListener('online', alertOnlineStatus)
// window.addEventListener('offline', alertOnlineStatus)

// alertOnlineStatus()

////////// Native File Drag & Drop
// const { ipcRenderer } = require('electron');
// document.getElementById('drag').ondragstart = (event) => {
//   event.preventDefault();
//   ipcRenderer.send('ondragstart', '/Users/xiaoyihan/Code/DaDa/distance-measure/GUI/my-electron-app/testIMG.jpg');
// }
