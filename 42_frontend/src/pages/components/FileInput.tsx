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
const MAX_FILE_SIZE = 1 * 1024 * 1024;
const TYPE_ALLOWED = ["text/plain"];

function FileInput() {
  const [file, setFile] = useState<File | null>(null);
  const [error, setError] = useState<string | null>(null);
  // const { user } = useUserStore();

  console.log("File input");

  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const file = e.target.files ? e.target.files[0] : null;
    console.log("setfile");
    console.log(file);
    if (file) {
      if (file.size > MAX_FILE_SIZE) {
        setError("1mb 이상의 파일만 가능합니다.");
        setFile(null);
      } else if (!TYPE_ALLOWED.includes(file.type)) {
        setError("파일의 타입은 텍스트만 가능합니다.");
        setFile(null);
      } else {
        setFile(file);
        setError(null);
      }
    }
  };

  const handleSubmit = async (e: React.FormEvent): Promise<Contenta | null> => {
    // const handleSubmit = () => {
    console.log("file submit??");
    console.log(file);
    e.preventDefault();
    if (file == null) {
      setError("파일을 선택해주세요!");
      return null;
    }
    console.log("send file -ing");
    const response = await $.post(`/api/chatroom/files`, file, {
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
      },
    })
      .then((res) => {
        setError(null);
        return res.data;
      })
      .catch(() => setError("file upload failed. try again"));
    return response;
  };

  return (
    <div>
      <form onSubmit={handleSubmit} className="file-input-form">
        <input type="file" onChange={handleFileChange} />
        <button type="submit">Upload File</button>
      </form>
      {error}
    </div>
  );
}

export default FileInput;
