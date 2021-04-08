const { app, BrowserWindow } = require('electron');
const path = require('path');
const url = require('url');
const ipc = require('electron').ipcMain;
let newwin;

function createWindow () {
  const win = new BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      preload: path.join(__dirname, 'preload.js')
    }
  })

  win.loadFile('html/index.html');
}

app.whenReady().then(() => {
  createWindow();

  app.on('activate', () => {
    if (BrowserWindow.getAllWindows().length === 0) {
      createWindow();
    }
  })
})

app.on('window-all-closed', () => {
  if (process.platform !== 'darwin') {
    app.quit()
  }
})

////////// Open new page
ipc.on('add', ()=>{
  newwin = new BrowserWindow({
    width: 800,
    height: 600,
    frame: false,
    parent: win, // win is the main window
  })
  newwin.loadURL( path.join('file:',__dirname,'html/userAccount.html') );
  newwin.on('close', ()=>{newwin = null})
})


////////// Custom the Dock Menu
const { Menu } = require('electron')
const dockMenu = Menu.buildFromTemplate([
  {
    label: 'New Window',
    click () { console.log('New Window') }
  }, {
    label: 'New Window with Settings',
    submenu: [
      { label: 'Basic' },
      { label: 'Pro' }
    ]
  },
  { label: 'New Command...' }
])

app.whenReady().then(() => {
  app.dock.setMenu(dockMenu);
})




////////// Online / Offline Event Detection
// let onlineStatusWindow;
// app.whenReady().then(() => {
//   onlineStatusWindow = new BrowserWindow({ width: 0, height: 0, show: false });
//   onlineStatusWindow.loadURL(`file://${__dirname}/index.html`);
// })

////////// Native File Drag & Drop
// const { ipcMain } = require('electron');
// ipcMain.on('ondragstart', (event, filePath) => {
//   event.sender.startDrag({
//     file: filePath,
//     icon: '/path/to/icon.png'
//   })
// })
