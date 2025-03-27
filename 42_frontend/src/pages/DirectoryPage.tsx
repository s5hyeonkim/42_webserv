import { useEffect, useState } from "react";
// import { useUserStore } from "../User.ts";
// import axios from "axios";
// import { $ } from "../axios";
import { $ } from "../axios";
import { useParams } from "react-router-dom";

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
  var { addr } = useParams();

  console.log("dir page1");
  useEffect(() => {
    console.log("dir page2");
    if (addr == null) addr = "/";
    fetchDirectoryData("/api/dir" + addr).then((data) => {
      setContent(data);
    });
  }, [addr]);
  if (!content) return <div> Loading</div>;
  // const [directories] = useState<Directory[]>([
  //   { id: 1, name: "Documents" },
  //   { id: 2, name: "Pictures" },
  //   { id: 3, name: "Music" },
  // ]);
  // const { user } = useUserStore();
  // const [newDir, setNewDir] = useState("");

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

  return (
    <div className="max-w-md mx-auto p-6 bg-white shadow-lg rounded-lg">
      <h2 className="text-xl font-semibold mb-4">📂 Directory List</h2>
      %.
      <ul className="mb-4">
        {content.map((dir, id) => (
          <li key={id} className="p-2 border-b">
            📁 {dir.file_name}
            {dir.file_date}
            {dir.file_size}
          </li>
        ))}
      </ul>
      <form onSubmit={handleSubmit} className="file-input-form">
        <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
    </div>
  );
}
2;
