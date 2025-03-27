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
    e.preventDefault();
    if (file == null) return null;

    console.log("send file -ing");
    const formData = new FormData();
    const user = { user_id: 1, user_name: "aa" };
    formData.append("user_id", user!.user_id.toString()); // Append userId
    formData.append("content", file);
    for (let [key, value] of formData.entries()) {
      console.log(key, value);
    }
    const response = await $.post(`/api/chatroom/files`, formData, {
      headers: {
        "Content-Type": "multipart/form-data",
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
