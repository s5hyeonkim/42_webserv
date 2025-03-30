import { useState } from "react";
import { Content } from "../../Content";

type MessageItemProps = {
  message: Content;
  onDelete: (content_id: number) => void;
  onDownload?: (content_id: number) => void; // 파일 다운로드 함수 (선택적)
};

const MessageItem = ({ message, onDelete, onDownload }: MessageItemProps) => {
  const [showOptions, setShowOptions] = useState(false);

  const handleClick = () => {
    setShowOptions(true);
  };

  const handleClose = () => {
    setShowOptions(false);
  };

  return (
    <>
      <li onClick={handleClick} style={{ cursor: "pointer" }}>
        <strong>{message.user_name}:</strong>{" "}
        {message.is_exist ? (
          <span>{message.content}</span>
        ) : (
          <div>메시지가 삭제되었습니다.</div>
        )}
        <small>{message.timestamp}</small>
      </li>

      {/* 삭제/다운로드 선택 모달 */}
      {showOptions && (
        <div
          style={{
            position: "fixed",
            top: "50%",
            left: "50%",
            transform: "translate(-50%, -50%)",
            background: "white",
            padding: "20px",
            borderRadius: "10px",
            boxShadow: "0 4px 10px rgba(0,0,0,0.2)",
            zIndex: 1000,
          }}
        >
          <p>메시지를 어떻게 처리할까요?</p>
          {onDownload && (
            <button
              onClick={() => {
                onDownload(message.content_id);
                handleClose();
              }}
              style={{
                marginRight: "10px",
                padding: "5px 10px",
                cursor: "pointer",
              }}
            >
              다운로드
            </button>
          )}
          <button
            onClick={() => {
              if (window.confirm("정말 삭제하시겠습니까?")) {
                onDelete(message.content_id);
              }
              handleClose();
            }}
            style={{
              padding: "5px 10px",
              cursor: "pointer",
              background: "red",
              color: "white",
            }}
          >
            삭제
          </button>
          <button
            onClick={handleClose}
            style={{
              marginLeft: "10px",
              padding: "5px 10px",
              cursor: "pointer",
              background: "gray",
              color: "white",
            }}
          >
            취소
          </button>
        </div>
      )}
    </>
  );
};

export default MessageItem;
