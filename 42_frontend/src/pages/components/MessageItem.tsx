import { useState } from "react";
import { Content } from "../../Content";
import CommentManager from "./CommentManager";

type MessageItemProps = {
  message: Content;
  onFurther: boolean;
  onDelete: (content: Content) => void;
  onDownload?: (content_id: number) => void;
};

const MessageItem = ({ message, onDelete, onDownload, onFurther}: MessageItemProps) => {
  const [showOptions, setShowOptions] = useState(false);

  const handleClick = () => {
    if (onFurther)
      setShowOptions(true);
  };

  const handleClose = () => {
    setShowOptions(false);
  };
  
  const date = new Date(message.timestamp);
  console.log("Date");
  console.log(message.timestamp);
  console.log(date);
  const formattedDate = `${
    date.getMonth() + 1
  }월 ${date.getDate()}일 ${date.getHours()}시 ${date.getMinutes()}분`;
  return (
    <>
      <li className="message-container" onClick={handleClick} style={{ cursor: "pointer", listStyleType: "none" }}>
        <div className="user-name"><strong>{message.user_name}</strong></div>
        {message.is_exist ? (
  <div className="message-box">
    {/* Check if the message is a comment */}
    {message.is_comment ? (
      <span>{message.content}</span>
    ) : (
      <span>파일을 업로드하였습니다.</span>
    )}
  </div>
) : (
  <span>메시지가 삭제되었습니다.</span>
)}
        <div className="date-container">
        <small>{formattedDate}</small>
        </div>
      </li>
    {showOptions && (<CommentManager message={message} onDelete={onDelete} onDownload={onDownload} handleClose={handleClose} />)}
    </>
  );
};

export default MessageItem;
