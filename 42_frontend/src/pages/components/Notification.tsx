// import { useEffect } from "react";
// import "./Card.css";

// type NotificationProps = {
//   msg: string;
//   isEnter: boolean;
//   onClose: () => void;
// };

// const Notification = ({ msg, isEnter, onClose }: NotificationProps) => {
//   useEffect(() => {
//     const timer = setTimeout(() => {
//       onClose();
//     }, 3000);
//     return () => clearTimeout(timer);
//   }, [onClose]);

//   return (
//     <div className="notification">
//       <div className="notification-content">
//         <p>
//           {msg} {isEnter ? "님이 들어왔습니다." : "님이 나갔습니다"}
//         </p>
//         <button onClick={onClose}>닫기</button>
//       </div>
//     </div>
//   );
// };

// export default Notification;
