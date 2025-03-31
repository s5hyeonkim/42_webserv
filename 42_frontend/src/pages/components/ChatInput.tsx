// import { useState } from "react";
// import "./ChatInput.css";
// import { $ } from "../../axios.ts";
// import useContentStore, { Content } from "../../Content.ts";
// import { getUserId } from "../../Auth.tsx";

// export function ChatInput() {
//   const [text, setText] = useState("");
//     const [file, setFile] = useState<File | null>(null);
//     const [error, setError] = useState<string | null>(null);
  
//   const { addContent } = useContentStore();
//   const userId = getUserId();

//   console.log("checkuser");
//   console.log(userId);
//   console.log("text");
//   console.log(text);

//   const handleFileChange = (e: React.ChangeEvent<HTMLInputElement>) => {
//     const file = e.target.files ? e.target.files[0] : null;
//     console.log("setfile");
//     console.log(file);
//     if (file) {
//       if (file.size > MAX_FILE_SIZE) {
//         setError("1mb 이상의 파일만 가능합니다.");
//         setFile(null);
//       } else if (!TYPE_ALLOWED.includes(file.type)) {
//         setError("파일의 타입은 텍스트만 가능합니다.");
//         setFile(null);
//       } else {
//         setFile(file);
//         setError(null);
//       }
//     }
//   };

//   const sendFile = async (e: React.FormEvent): Promise<Content | null> => {
//       console.log("file submit??");
//       console.log(file);
//       e.preventDefault();
//       if (file == null) {
//         setError("파일을 선택해주세요!");
//         return null;
//       }
//       console.log("send file -ing");
//       const response = await $.post(`/api/chatroom/files`, file, {
//         headers: {
//           "Content-Type": "application/x-www-form-urlencoded",
//         },
//       })
//         .then((res) => {
//           setError(null);
//           return res.data;
//         })
//         .catch(() => setError("file upload failed. try again"));
//       return response;
//     };
  
//   const sendComment = async () => {
//     const response = await $.post(`/api/chatroom/comments`, {
//       user_id: userId?.toString(),
//       content: text,
//     });
//     setText("");
//     if (response.data) addContent(response.data);
//     console.log(response);
//   };

//   return (
//     <form onSubmit={sendComment} className="chat-input-form">
//       <input
//         type="text"
//         value={text}
//         onChange={(e) => setText(e.target.value)}
//         placeholder="메시지를 입력해주세요"
//         className="chat-input"
//       />
//       <button type="submit">보내기</button>
//       <input type="file" onChange={handleFileChange} />
//     </form>
//   );
// }

// export default ChatInput;
