const { timeStamp } = require("console");
const fs = require("fs");
const express = require("express");
const path = require("path");
const mime = require("mime-types");
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
var data3 = {
  filelist: [
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
  ],
};
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
app.get("/qwe", (req, res) => {
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
  // res.setHeader("Location", "/chatroom");
  const users = {
    redirect: {
      redirect_url: "/chatroom",
    },
    body: {
      user_id: "1",
      user_name: req.body?.user_name,
    },
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
    timestamp: Date.now(),
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
  res.status(404).send({
    redirect: {
      redirect_url: "/40x.html",
    },
  });
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

app.post("/api/chatroom/files/download", (req, res) => {
  console.log("files arrived");
  console2.log(req.headers["content-type"]);
  console.log(req.body);
  res.json(data2);
});

const files = {
  9090: {
    file_name: "example.txt",
    file_path: "./files/example.txt", // Assuming this file exists in the "files" folder
  },
  // Add more files as needed
};

app.get("/api/chatroom/files/download/:contentId", (req, res) => {
  const contentId = req.params.contentId;
  const file = files[contentId];

  if (!file) {
    return res.status(404).json({ error: "File not found" });
  }

  const { file_name, file_path } = file;

  // Check if file exists
  fs.stat(file_path, (err, stats) => {
    if (err || !stats.isFile()) {
      return res
        .status(500)
        .json({ error: "File does not exist on the server" });
    }

    // Set the correct MIME type for the file
    const mimeType = mime.lookup(file_name) || "application/octet-stream";

    // Set the response headers
    res.setHeader("Content-Disposition", `attachment; filename="${file_name}"`);
    res.setHeader("Content-Type", mimeType);
    res.setHeader("Content-Length", stats.size);

    // Pipe the file content to the response
    const fileStream = fs.createReadStream(file_path);
    fileStream.pipe(res);

    // Handle errors during streaming
    fileStream.on("error", (error) => {
      res.status(500).json({ error: "Error streaming the file" });
    });
  });
});

app.listen(port, () => {
  console.log(`Server is running at localhost:${port}`);
});
