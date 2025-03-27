import React, { useState } from "react";
import "./FileInput.css";
// import { useUserStore } from "../../User.ts";
import { $ } from "../../axios.ts";
// import { Content } from "../../Content.ts";
// import { $ } from "../../axios.ts";
// import axios from "axios";

interface Contenta {
  user_id: number;
  user_name: string;
  content_id: number;
  content: string;
  is_exist: boolean;
  is_comment: boolean;
  timestamp: number;
}

function FileInput() {
  const [file, setFile] = useState<File | null>(null);
  // const { user } = useUserStore();

  console.log("File input");
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
    <form onSubmit={handleSubmit} className="file-input-form">
      <input type="file" onChange={handleFileChange} />
      <button type="submit">Upload File</button>
    </form>
  );
}

export default FileInput;
