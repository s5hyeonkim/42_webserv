import React, { useState } from "react";
// import useContentStore, { Content } from '../../Content';
import { Content } from "../../Content";
import { $ } from "../../axios";
import { getUserId } from "../../Auth";
import { Toast } from "./toast";

const Input = () => {
  const [isCommentMode, setIsCommentMode] = useState(true);
  const [file, setFile] = useState<File | null>(null);
  const [comment, setComment] = useState("");
  // const [isLoading, setLoading] = useState(false);
  // const { addDisplayedContent } = useContentStore();
  const userId = getUserId();

  const sendFile = async () => {
    console.log("file submit??");
    console.log(file);
    console.log("send file -ing");
    const response = await $.post(`/api/chatroom/files`, file, {
      headers: {
        "Content-Type": "application/x-www-form-urlencoded",
      },
    })
      .then((res) => {
        // addDisplayedContent(res.data);
        setFile(null);
        return res.data;
      })
      .catch(() => Toast.error("파일 업로드에 실패하였습니다."));
    return response;
  };

  const sendComment = async () => {
    const response = await $.post(`/api/chatroom/comments`, {
      user_id: userId?.toString(),
      content: comment,
    })
      .then((res) => {
        // addDisplayedContent(res.data);
        setComment("");
        return res.data;
      })
      .catch(() => Toast.error("메시지 보내기를 실패하였습니다."));
    console.log(response);
  };

  const handleSend = async (e: React.FormEvent): Promise<Content | void> => {
    e.preventDefault();
    if (isCommentMode) {
      if (comment) sendComment();
      else Toast.error("텍스트를 입력해주세요!");
    } else if (!isCommentMode && file) sendFile();
    else Toast.error("파일을 넣어주세요!");
  };
  const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
    const selectedFile = e.target.files ? e.target.files[0] : null;
    setFile(selectedFile);
    // setComment(`파일 이름: ${e.target.files?.item.name}을 업로드하였습니다.`);
    setIsCommentMode(!selectedFile);
  };
  const handleKeyDown = (e: React.KeyboardEvent<HTMLTextAreaElement>) => {
    if (e.key === "Enter") {
      e.preventDefault();
      handleSend(e);
    }
  };

  return (
    <div>
      <textarea
        placeholder="메시지 입력"
        value={comment}
        onChange={(e) => setComment(e.target.value)}
        onKeyDown={handleKeyDown}
        style={{
          width: "100%",
          height: "70px",
          resize: "none",
        }}
      />
      <div className="input-change">
        <input type="file" onChange={handleFileChange} />
        <button
          onClick={handleSend}
          style={{
            position: "fixed",
            right: "20px",
            border: "1px solid black",
            borderRadius: "10px",
            background: "none",
            cursor: "pointer",
            padding: "10px 20px",
          }}
        >
          보내기
        </button>
      </div>
    </div>
  );
};

export default Input;
