import { useState } from "react";
import { $ } from "../../axios";
import { Content } from "../../Content";

type MessageItemProps = {
  message: Content;
};

const MessageItem = ({ message }: MessageItemProps) => {
  const [error, setError] = useState<string | null>(null);
  const deleteFile = async () => {
    await $.delete(`/api/chatrooom/files/${message.content_id}`)
      .then(() => {})
      .catch(() => setError("파일 삭제에 실패하였습니다."));
  };
  const deleteComment = async () => {
    await $.delete(`/api/chatrooom/comments/${message.content_id}`)
      .then(() => {})
      .catch(() => setError("글 삭제에 실패하였습니다."));
  };

  const handleDelete = () => {
    if (window.confirm("정말 메시지를 삭제하시겠습니까?")) {
      if (message.is_comment) deleteComment();
      else deleteFile();
    }
  };
  const closeError = () => {
    setError(null);
  };
  return (
    <div>
      {error && (
        <div
          style={{
            position: "fixed",
            top: "20px",
            left: "50%",
            transform: "translateX(-50%)",
            background: "red",
            color: "white",
            padding: "10px",
            borderRadius: "5px",
            zIndex: 1000,
          }}
        >
          {error}
          <button
            onClick={closeError}
            style={{
              marginLeft: "10px",
              background: "white",
              color: "red",
              border: "none",
              cursor: "pointer",
            }}
          >
            닫기
          </button>
        </div>
      )}
      <li onClick={handleDelete} style={{ cursor: "pointer" }}>
        <strong>{message.user_name}:</strong>{" "}
        {message.is_exist ? (
          <span>{message.content}</span>
        ) : (
          <div>메시지가 삭제되었습니다.</div>
        )}
        <small>{message.timestamp}</small>
      </li>
    </div>
  );
};

export default MessageItem;
