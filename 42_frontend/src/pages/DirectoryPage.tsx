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

const convertTimestampToDate = (timestamp: number): string => {
  const date = new Date(timestamp * 1000); // 유닉스 타임스탬프는 초 단위이므로 밀리초로 변환
  return date.toLocaleString(); // 기본적으로 로컬 형식으로 날짜를 변환
};

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
<h2 className="dir-subject">📁 디렉토리 검색</h2>

<table className="directory-table">
  <thead>
    <tr>
      {/* <th/> */}
      <th style={{}}>파일 이름</th>
      <th>마지막 변경 시각</th>
      <th>사이즈</th>
    </tr>
  </thead>
  <tbody>
    {content.map((item, index) => (
      <tr key={index}>
        {/* <td className="icon">{item.file_name.endsWith("\\") ? "📁" : "📄"}</td> */}
        <td className="name">{item.file_name.endsWith("\\") ? "📁" : "📄"}{item.file_name}</td>
        <td className="info">{convertTimestampToDate(item.file_date)}</td>
        <td className="size">{item.file_size}</td>
      </tr>
    ))}
  </tbody>
</table>
      <form onSubmit={handleSubmit} className="file-input-form">
        <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
    </Fragment>
  );
}
