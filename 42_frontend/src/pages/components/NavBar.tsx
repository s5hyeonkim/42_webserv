import { useState } from "react";
import logoImageSmall from "../../assets/logo.svg";
import Modal from "./Modal.tsx";
import "./NavBar.css";
import { useNavigate } from "react-router-dom";
import { $ } from "../../axios.ts";
import { useAuth } from "../../Auth.tsx";

function NavBar() {
  const [isModalOpen, setIsModalOpen] = useState(false);

  const toggleModal = () => {
    setIsModalOpen(!isModalOpen);
  };
  const navigate = useNavigate();
  const { login } = useAuth();

  const sendUserInfo = async (query: string) => {
    const res = await $.post("/api/users/register", {
      user_name: query,
    })
      .then((res) => res.data)
      .catch((error) => {
        return error;
      });
    console.log("inputText: ");
    console.log(query);
    console.log("data");
    console.log(res);
    console.log(res.body);
    login(Number(res.body.user_id));
    console.log("redirect url received");
    console.log(res.redirect.redirect_url);
    navigate(res.redirect.redirect_url, { replace: true });
  };

  return (
    <div className="navbar">
      <div className="logo-container">
        <img src={logoImageSmall} alt="Logo" />
      </div>

      <div className="right-container">
        <a href="/main" className="nav-home">
          Home
        </a>
        <button onClick={toggleModal} className="nav-chat-btn">
          Go to Chat
        </button>
        <Modal
          isOpen={isModalOpen}
          onClose={() => setIsModalOpen(false)}
          onSubmit={sendUserInfo}
        >
          <h2> 채팅방 입장 </h2>
        </Modal>
      </div>
    </div>
  );
}

export default NavBar;
