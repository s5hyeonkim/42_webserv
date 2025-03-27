// import NavBar from "./pages/components/NavBar";
// import MainPage from "./pages/MainPage";
// import BottomNavBar from "./pages/components/BottomNavBar";

import { Outlet } from "react-router-dom";

// import { Outlet } from "react-router-dom";

function App() {
  return (
    <div className="app">
      <Outlet />
      {/* <NavBar /> /*/}
      {/* <MainPage /> */}
      {/* <ChatPage /> */}
      {/* <BottomNavBar /> */}
    </div>
  );
}

export default App;
