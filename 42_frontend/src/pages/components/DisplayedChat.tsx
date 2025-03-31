import useContentStore, { Content } from "../../Content.ts";
import MessageItem from "./MessageItem.tsx";
import { $ } from "../../axios.ts";
// import { useState } from "react";

function DisplayedChat() {
  // const { data, isLoading } = getChattingList();
  const {
    // setContents,
    // addContent,
    // setOldContents,
    // recentContents,
    displayedContents
    // setRecentContents,
    // deletedContents,
    // setDeletedContents,
  } = useContentStore();
  const now = new Date();
  const handleFurther = (timestamp: number) => {
    return now.getTime() - timestamp < 1000 * 60 * 5;
  }
  const handleDelete = (message: Content) => {
    if (message.is_comment)
        handleDeleteComment(message.content_id);
    else
        handleDeleteFile(message.content_id);
    return true;
}
  const handleDeleteFile = async (content_id: number) => {
    await $.delete(`/api/chatroom/files/${content_id}`)
      .then(() => {})
      .catch(() => {
        return "파일 삭제에 실패하였습니다.";
      });
  };
  const handleDeleteComment = async (content_id: number) => {
    await $.delete(`/api/chatroom/comments/${content_id}`)
      .then(() => {})
      .catch(() => {
        return "파일 삭제에 실패하였습니다.";
      });
  };
  const handleDownloadFile = async (content_id: number) => {
    try {
      const response = await $.get(
        `/api/chatroom/files/download/${content_id}`,
        {
          headers: {
            Accept: "application/octet-stream",
          },
        }
      );
      const blob = new Blob([response.data], {
        type: "appication/octet-stream",
      });

      const link = document.createElement("a");
      link.href = URL.createObjectURL(blob);
      link.download = "42-chat-downloaded-file.txt";
      link.click();
      URL.revokeObjectURL(link.href);
    } catch (err) {
      console.log(err);
      return "Download failed. Please try again.";
    }
  };

  // if (isLoading) return <p> Chatting Page를 불러오고 있습니다.</p>;
  return (
    <div
      className="chat-display"
      // style={{ maxHeight: "400px", overflowY: "scroll" }}
    >

      {/* {recentContents.map((message) => ( */}
      {displayedContents.map((message) => (
        <MessageItem
          key={message.content_id}
          message={message}
          onDelete={handleDelete}
          onDownload={message.is_comment ? undefined : handleDownloadFile}
          onFurther = {handleFurther(message.timestamp)}
        />
      ))}
    </div>
  );
}

export default DisplayedChat;
