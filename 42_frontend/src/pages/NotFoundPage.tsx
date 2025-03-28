import { useState } from "react";
import { Outlet } from "react-router-dom";
import { $ } from "../axios";
// import { Outlet, useLocation } from "react-router-dom";
// import DirectoryPage from "./DirectoryPage";
interface Contenta {
  user_id: number;
  user_name: string;
  content_id: number;
  content: string;
  is_exist: boolean;
  is_comment: boolean;
  timestamp: number;
}

const NotFoundPage = () => {
  const [file, setFile] = useState<File | null>(null);

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

  console.log("not found page");

  return (
    <div>
      <Outlet />
      <div>NotFOund</div>
      <form onSubmit={handleSubmit} className="file-input-form">
        <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
    </div>
  );
};

export default NotFoundPage;
