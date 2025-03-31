const fs = require("fs");
const express = require("express");
const mime = require("mime-types");
const app = express();
const port = 2424;
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
      user_id: "3",
      user_name: "abcbc",
      content_id: "11",
      content: "this is comment",
      is_comment: 1,
      is_exist: 1,
      timestamp: 1743393564144,
    },
    {
      user_id: "2",
      user_name: "qweqwe",
      content_id: "11",
      content: "this is comment",
      is_comment: 1,
      is_exist: 1,
      timestamp: 1743393564344,
    },
  ],
};
var data2 = {
  user_id: 1,
  user_name: "aa",
  content_id: 11,
  content: "",
  is_exist: true,
  is_comment: false,
  timestamp: 1231231222,
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
    "C:\\Users\\alice\\Desktop\\webserv\\mine\\42_frontend\\dist\\assets"
    // "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\assets"
  )
);
app.use(express.json());
app.get("/", (req, res) => {
  res.sendFile(
    // "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
    "C:\\Users\\alice\\Desktop\\webserv\\mine\\42_frontend\\dist\\index.html"
  );
});
app.delete("/api/chatroom/files/:contentId", (req, res) => {
  const contentId = req.params.contentId;
  console.log(contentId);
});
app.delete("/api/chatroom/comments/:contentId", (req, res) => {
  const contentId = req.params.contentId;
  console.log(contentId);
});
app.post("/api/users/register", (req, res) => {
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
  // console.log("data:");
  // console.log(data);
  res.json(data);
});

app.get("/api/chatroom", (req, res) => {
  console.log("/api/chatroom request");
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
  console.log("/api/chatroom/comments request");
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
  fs.stat(file_path, (err, stats) => {
    if (err || !stats.isFile()) {
      return res0
        .status(500)
        .json({ error: "File does not exist on the server" });
    }
    const mimeType = mime.lookup(file_name) || "application/octet-stream";
    res.setHeader("Content-Disposition", `attachment; filename="${file_name}"`);
    res.setHeader("Content-Type", mimeType);
    res.setHeader("Content-Length", stats.size);
    const fileStream = fs.createReadStream(file_path);
    fileStream.pipe(res);
    fileStream.on("error", (error) => {
      res.status(500).json({ error: "Error streaming the file" });
    });
  });
});
app.get("/*", (req, res) => {
  console.log(req.originalUrl);
  res.sendFile(
    "C:\\Users\\alice\\Desktop\\webserv\\mine\\42_frontend\\dist\\index.html"
    // "C:\\Users\\alice\\OneDrive\\바탕 화면\\중요\\webserv\\42_frontend\\dist\\index.html"
  );
});

app.listen(port, () => {
  console.log(`Server is running at localhost:${port}`);
});
