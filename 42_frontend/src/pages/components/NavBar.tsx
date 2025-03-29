import { useState } from "react";
import logoImageSmall from "../../assets/logo.svg";
import Modal from "./Modal.tsx";
import "./NavBar.css";
import { useNavigate } from "react-router-dom";
// import { useUserStore } from "../../User.ts";
import { $ } from "../../axios.ts";
import { useAuth } from "../../Auth.tsx";

function NavBar() {
  const [isModalOpen, setIsModalOpen] = useState(false);

  const toggleModal = () => {
    setIsModalOpen(!isModalOpen);
  };
  const navigate = useNavigate();
  // const { setUser } = useUserStore();
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
    // setUser(res.body);
    login(Number(res.body.user_id));
    navigate(res.redirect.redirect_url, { replace: true });
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
        <Modal
          isOpen={isModalOpen}
          onClose={() => setIsModalOpen(false)}
          onSubmit={sendUserInfo}
        >
          <h2> 채팅방 입장 </h2>
          {/* <p>This modal lets you enter a search term and fetch data!</p> */}
        </Modal>
      </div>

      {/* Modal Component */}
    </div>
  );
}

export default NavBar;
