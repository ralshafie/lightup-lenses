$(document).ready(function(){
  console.log("hi")
});

//when the user clicks anywhere on the page
document.addEventListener('click', async () => {
    // Prompt user to select any serial port.
    var port = await navigator.serial.requestPort();
    // be sure to set the baudRate to match the ESP32 code
    await port.open({ baudRate: 115200 });
  
    let decoder = new TextDecoderStream();
    inputDone = port.readable.pipeTo(decoder.writable);
    inputStream = decoder.readable;
  
    reader = inputStream.getReader();

    readLoop();
});

var bg_color = 0 ;
var redVal = 0; 
  
async function readLoop() {
  counterVal = 0;
  while (true) {
    const { value, done } = await reader.read();
    if (done) {
      // Allow the serial port to be closed later.
      console.log("closing connection")
      reader.releaseLock();
      break;
    }
    
    if (value) {
      try {
        a = JSON.parse(value);
        redIn = a["dial"][0];
        greenIn = a["dial"][1];
        blueIn = a["dial"][2]; 
        
        //DIAL from 0 to 4095, we want 0 to 255
        redVal = redIn/16; 
        greenVal = greenIn/16; 
        blueVal = blueIn/16; 
       

        //change background color
        document.body.style.backgroundColor = 'rgb(' + redVal + ','+ greenVal + ',' + blueVal+')';

        //add vals to HTML
        document.getElementById("redVal").textContent= redIn;
        document.getElementById("greenVal").textContent = greenIn;
        document.getElementById("blueVal").textContent = blueIn; 
      } catch(e) {
        console.log(value); // error in the above string (in this case, yes)!
      }
    }
  }
};

