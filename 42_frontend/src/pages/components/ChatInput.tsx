import { useState } from "react";
import "./ChatInput.css";
import { useUserStore } from "../../User.ts";
import { $ } from "../../axios.ts";
import useContentStore from "../../Content.ts";

export function ChatInput() {
  const [text, setText] = useState("");
  const { user } = useUserStore();
  const { addContent } = useContentStore();
  // const handleCommentChange = () => {
  //   setText(text);2
  // };
  console.log("checkuser");
  console.log(user);
  console.log(user?.user_id);
  console.log(user?.user_name);
  console.log("text");
  console.log(text);
  const sendComment = async () => {
    const response = await $.post(`/api/chatroom/comments`, {
      user_id: user!.user_id,
      content: text,
    });
    setText("");
    if (response.data) addContent(response.data);
    console.log(response);
  };

  return (
    <form onSubmit={sendComment} className="chat-input-form">
      <input
        type="text"
        value={text}
        onChange={(e) => setText(e.target.value)}
        placeholder="메시지를 입력해주세요"
        className="chat-input"
      />
      <button type="submit">Send</button>
    </form>
  );
}

export default ChatInput;
