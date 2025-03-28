const { timeStamp } = require("console");
const express = require("express");
const path = require("path");
const { stringify } = require("querystring");
const app = express();
const port = process.env.PORT || 2424;
var data = {
  users: [
    {
      user_id: "1",
      user_name: "a",
    },
    {
      user_id: "2",
      user_name: "b",
    },
  ],
  contents: [
    {
      user_id: "2",
      user_name: "a",
      content_id: "11",
      content: "this is comment",
      is_comment: 1,
      is_exist: 1,
      timestamp: "1231325",
    },
  ],
};
var data2 = {
  user_id: 1,
  user_name: "aa",
  content_id: 11,
  conetnt: "",
  is_exist: true,
  is_comment: false,
  timestampe: 1231231222,
};
var data3 = [
  {
    file_name: "aa",
    file_date: 1473111231,
    file_size: 1111,
  },
  {
    file_name: "bb",
    file_date: 1573111231,
    file_size: 1111,
  },
  {
    file_name: "cc",
    file_date: 1673121111,
    file_size: 1111,
  },
];
app.use(
  "/assets",
  express.static(
    "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\assets"
  )
);
app.use(express.json());
app.get("/", (req, res) => {
  res.sendFile(
    // "index.html"
    "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
  );
});
app.get("/dir", (req, res) => {
  res.sendFile(
    "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
    // "index.html"
    // "C:\\Users\\alice\\Desktop\\webserv\\webserv\\42_frontend\\dist\\index.html"
  );
});
app.get("/dir/*", (req, res) => {
  res.sendFile(
    // "index.html"
    "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
    // "C:\\Users\\alice\\Desktop\\webserv\\webserv\\42_frontend\\dist\\index.html"
  );
});
app.get("/assets", (req, res) => {
  res.sendFile();
});
app.get("/main", (req, res) => {
  res.sendFile(
    // "index.html"
    "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
    // "C:\\Users\\alice\\Desktop\\webserv\\webserv\\42_frontend\\dist\\index.html"
  );
});
app.get("/chatroom", (req, res) => {
  console.log("into chatroompage");
  res.sendFile(
    "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
    // "C:\\Users\\alice\\Desktop\\webserv\\webserv\\42_frontend\\dist\\index.html"
    // "index.html"
  );
  console.log("into chatroompage2220");
});
app.post("/api/users/register", (req, res) => {
  // console.log("register");
  // console.log(req.body);
  // console.log(req.data);
  res.setHeader("Location", "/chatroom");
  const users = {
    user_id: "1",
    user_name: req.body?.user_name,
    redirect_url: "/chatroom",
  };
  res.json(users);
});
app.post("/api/chatroom/comments", (req, res) => {
  console.log("comment arrived");
  // console.log(req);
  // console.log(req.body);
  const content = {
    user_id: req.body.user_id,
    user_name: "a",
    content_id: 11,
    content: req.body.content,
    is_comment: 1,
    is_exist: 1,
    timestamp: 1232312312,
  };
  data.contents.push(content);
  console.log("data:");
  console.log(data);
  res.json(data);
});

app.get("/api/chatroom", (req, res) => {
  res.json(data);
});

app.get("/api/dir", (req, res) => {
  console.log("dir page");
  res.json(data3);
});

app.get("/api/dir/*", (req, res) => {
  console.log("dir page");
  res.json(data3);
});

app.get("/api/chatroom/comments", (req, res) => {
  res.json(data);
});

app.post("/api/chatroom/files", (req, res) => {
  console.log("files arrived");
  console.log(req.headers["content-type"]);
  console.log(req.body);
  res.json(data2);
});

app.listen(port, () => {
  console.log(`Server is running at localhost:${port}`);
});
