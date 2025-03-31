import { useUserStore } from "../../User.ts";
import useContentStore from "../../Content.ts";
import MessageItem from "./MessageItem.tsx";
import { $ } from "../../axios.ts";

function RecentChats() {
  // const { data, isLoading } = getChattingList();
  const {
    // user,
    // users,
    // setUsers,
    newUsers,
    // setNewUsers,
    deletedUsers,
    // setDeletedUsers,
  } = useUserStore();
  const {
    // setContents,
    // addContent,
    // setOldContents,
    recentContents,
    // setRecentContents,
    // deletedContents,
    // setDeletedContents,
  } = useContentStore();
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
      style={{ maxHeight: "400px", overflowY: "scroll" }}
    >
      <ul>
        {deletedUsers?.map((user) => (
          <li key={user.user_id} style={{ color: "red" }}>
            {user.user_name} 님이 퇴장하셨습니다.
          </li>
        ))}
      </ul>
      <ul>
        {newUsers?.map((user) => (
          <li key={user.user_id} style={{ color: "green" }}>
            {user.user_name} 님이 입장하셨습니다.
          </li>
        ))}
      </ul>
      {recentContents.map((message) => (
        <MessageItem
          key={message.content_id}
          message={message}
          onDelete={message.is_comment ? handleDeleteComment : handleDeleteFile}
          onDownload={message.is_comment ? undefined : handleDownloadFile}
        />
      ))}
    </div>
  );
}

export default RecentChats;
