import { Fragment, useEffect, useState } from "react";
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

const convertTimestampToDate = (timestamp: number): string => {
  const date = new Date(timestamp * 1000); // 유닉스 타임스탬프는 초 단위이므로 밀리초로 변환
  return date.toLocaleString(); // 기본적으로 로컬 형식으로 날짜를 변환
};

const fetchDirectoryData = async (addr: string): Promise<Directory[]> => {
  console.log("request to server to ");
  console.log(addr);
  const response = await $.get(addr).then((res) => res.data);
  console.log(response);
  return response.filelist;
};

export default function DirectoryPage() {
  const [content, setContent] = useState<Directory[] | []>([]);
  const location = useLocation();

  useEffect(() => {
    console.log("location");
    console.log(location);
    fetchDirectoryData("/api" + location.pathname).then((data) => {
      setContent(data);
    });
  }, [location]);
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
              <td className="name">
                {item.file_name.endsWith("\\") ? "📁" : "📄"}
                {item.file_name}
              </td>
              <td className="info">{convertTimestampToDate(item.file_date)}</td>
              <td className="size">{item.file_size}</td>
            </tr>
          ))}
        </tbody>
      </table>
    </Fragment>
  );
}
