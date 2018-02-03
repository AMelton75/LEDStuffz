function strobe() {
var x = document.getElementsByTagName("BODY")[0];
x.BackColor = black;
await sleep(200);
x.BackColor = white;
}
