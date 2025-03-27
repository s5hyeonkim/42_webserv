import Card from "./components/Card.tsx"; // Import the Card component
import logoImageMedium from "../assets/logoMain.svg";
import { cardData } from "./components/cardData.ts";
import "./MainPage.css";
import { Fragment } from "react/jsx-runtime";
import NavBar from "./components/NavBar.tsx";
import BottomNavBar from "./components/BottomNavBar.tsx";
import { Outlet } from "react-router-dom";

// const mainData = [
//   {
//     image: cardImage1,
//     subhead: "Instant Messaging",
//     description: 'Say goodbye to "I\'m on my way"delays.\nOut',
//   },
//   {
//     image: cardIm2age2,
//     subhead: "Group Chats",
//     description: "This is the description for card 2.",
//   },
//   {
//     image: cardImage3,
//     subhead: "Send Anything!",
//     description: "This is the description for card 3.",
//   },
// ];

const MainPage = () => {
  return (
    <Fragment>
      <NavBar />
      <Outlet />

      <div className="main-container">
        {/* <div className="divider"></div> */}
        <img src={logoImageMedium} alt="LogoMedium" />
        <h2>Main Content</h2>
        <p>
          This is the body text of the main section. You can add more content
          here.
        </p>
        <div className="cards">
          {cardData.map((card, index) => (
            <div>
              <Card
                key={`card-${index}`}
                image={card.image}
                subhead={card.subhead}
                description={card.description}
              />
              <div
                style={{
                  display: index != 2 ? "block" : "none",
                  background: "#dfc7b8",
                  height: 20,
                  width: 540,
                  marginTop: "55px",
                  marginBottom: "55px",
                }}
              ></div>
            </div>
          ))}
        </div>
      </div>
      <BottomNavBar />
    </Fragment>
  );
};

export default MainPage;
