import { useState } from "react";
import logoImageSmall from "../../assets/logo.svg";
import Modal from "./Modal.tsx";
import "./NavBar.css";

function NavBar() {
  const [isModalOpen, setIsModalOpen] = useState(false);

  const toggleModal = () => {
    setIsModalOpen(!isModalOpen);
  };

  return (
    <div className="navbar">
      {/* Left Logo (SVG) */}
      <div className="logo-container">
        <img src={logoImageSmall} alt="Logo" />
        {/* <span>MyApp</span> */}
      </div>

      {/* Right Home Link and Button */}
      <div className="right-container">
        <a href="/" className="nav-home">
          Home
        </a>
        <button onClick={toggleModal} className="nav-chat-btn">
          Go to Chat
        </button>
        <Modal isOpen={isModalOpen} onClose={toggleModal}>
          <h2> 채팅방 입장 </h2>
          {/* <p>This modal lets you enter a search term and fetch data!</p> */}
        </Modal>
      </div>

      {/* Modal Component */}
    </div>
  );
}

export default NavBar;
