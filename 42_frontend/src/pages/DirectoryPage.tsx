import { Fragment, useEffect, useState } from "react";
// import { useUserStore } from "../User.ts";
// import axios from "axios";
// import { $ } from "../axios";
import { $ } from "../axios";
import "./DirectoryPage.css";
import { useLocation } from "react-router-dom";

interface Directory {
  file_name: string;
  file_date: number;
  file_size: number;
}
interface Contenta {
  user_id: number;
  user_name: string;
  content_id: number;
  content: string;
  is_exist: boolean;
  is_comment: boolean;
  timestamp: number;
}

const fetchDirectoryData = async (addr: string): Promise<Directory[]> => {
  const response = await $.get(addr).then((res) => res.data);
  console.log(response);
  return response;
};

export default function DirectoryPage() {
  const [content, setContent] = useState<Directory[] | []>([]);
  const [file, setFile] = useState<File | null>(null);
  const location = useLocation();

  useEffect(() => {
    console.log("location");
    console.log(location);
    fetchDirectoryData("/api"+ location.pathname).then((data) => {
      setContent(data);
    });
  }, [location]);

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files ? e.target.files[0] : null;
    console.log("setfile");
    console.log(file);
    if (file) setFile(file);
  };

  const handleSubmit = async (e: React.FormEvent): Promise<Contenta | null> => {
    // const handleSubmit = () => {
    console.log("file submit??");
    console.log(file);
    e.preventDefault();
    if (file == null) return null;
    console.log("send file -ing");
    const response = await $.post(`/api/chatroom/files`, file, {
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
      },
    }).then((res) => res.data);
    return response;
  };
  if (!content) return <div> Loading</div>;

  return (
<Fragment>
<h2 className="dir-subject">📁 디렉토리 찾아보기</h2>

<div className="file-browser">
  <div className="tag-item">
  <span className="tag-name">파일 이름</span>
<span className="tag-name">마지막 변경 시각</span>
<span className="tag-size">사이즈</span>

  </div>

      <ul className="directory-list">
        {content.map((item, index) => (
          <li key={index} className="list-item">
<span className="icon">{item.file_name.endsWith("\\") ? "📁" : "📄"}</span>
<span className="name">{item.file_name}</span>
<span className="info">{item.file_date} </span>
<span className="size">{item.file_size} </span>
          </li>
        ))}
      </ul>
      <form onSubmit={handleSubmit} className="file-input-form">
        <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
    </div>
    </Fragment>
  );
}
