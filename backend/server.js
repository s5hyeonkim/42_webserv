const express = require("express");
const path = require("path");
const app = express();
const port = process.env.PORT || 3000;

app.use(express.static(path.join(__dirname, "../42_frontend/dist")));

app.get("*", (req, res) => {
  res.sendFile("../42_frontend/dist/index.html");
});
app.listen(port, () => {
  console.log(`Server is running at localhost:${port}`);
});
