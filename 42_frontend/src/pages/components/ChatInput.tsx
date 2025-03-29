import { useState } from "react";
import "./ChatInput.css";
import { $ } from "../../axios.ts";
import useContentStore from "../../Content.ts";
import { getUserId } from "../../Auth.tsx";

export function ChatInput() {
  const [text, setText] = useState("");
  const { addContent } = useContentStore();
  const userId = getUserId();

  console.log("checkuser");
  console.log(userId);
  console.log("text");
  console.log(text);
  const sendComment = async () => {
    const response = await $.post(`/api/chatroom/comments`, {
      user_id: userId?.toString(),
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
