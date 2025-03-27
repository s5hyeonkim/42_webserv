// import { useState } from "react";
// import "./NavBar.css";
// import Modal from "../pages/components/Modal";

// function NavBar() {
//   const [isModalOpen, setIsModalOpen] = useState(false);

//   const toggleModal = () => {
//     setIsModalOpen(!isModalOpen);
//   };

//   return (
//     <div className="navbar">
//       {/* Left Logo (SVG) */}
//       <div className="logo-container">
//         <img src="../src/assets/logo.svg" alt="Logo" />
//         {/* <span>MyApp</span> */}
//       </div>
//       {/* Right Home Link and Button */}.
//       <div className="right-container">
//         <a href="/" className="nav-home">
//           Home
//         </a>
//         <button onClick={toggleModal} className="nav-chat-btn">
//           Go to Chat
//         </button>
//         <Modal isOpen={isModalOpen} onClickToggleModal={toggleModal}>
//           <h2>Search Data</h2>
//           <p>This modal lets you enter a search term and fetch data!</p>
//         </Modal>
//       </div>
//       {/* Modal Component */}
//     </div>
//   );
// }

// export default NavBar;
