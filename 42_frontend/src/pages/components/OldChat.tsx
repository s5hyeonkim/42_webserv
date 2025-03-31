import useContentStore from "../../Content";
import MessageItem from "./MessageItem";
import { $ } from "../../axios";

const handleDownloadFile = async (content_id: number) => {
  try {
    const response = await $.get(`/api/chatroom/files/download/${content_id}`, {
      headers: {
        Accept: "application/octet-stream",
      },
    });
    const blob = new Blob([response.data], {
      type: "appication/octet-stream",
    });

    const link = document.createElement("a");
    link.href = URL.createObjectURL(blob);
    link.download = "42-chat-downloaded-file.txt";
    link.click();
    URL.revokeObjectURL(link.href);
  } catch (error) {
    return "Download failed. Please try again.";
  }
};
function OldChats() {
  const { oldContents } = useContentStore();
  // console.log("old");
  // console.log(oldContents);
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

  return (
    <div>
      <h2>Old Chat Messages (More than 5 minutes ago)</h2>
      <ul>
        {oldContents.map((message) => (
          <MessageItem
            key={message.content_id}
            message={message}
            onDelete={
              message.is_comment ? handleDeleteComment : handleDeleteFile
            }
            onDownload={message.is_comment ? undefined : handleDownloadFile}
          />
        ))}
      </ul>
    </div>
  );
}
export default OldChats;
