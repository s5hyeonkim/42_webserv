import { Outlet } from "react-router-dom";

const ServerErrorPage = () => {
  console.log("server error page");

  return (
    <div>
      <Outlet />
      <div>ErrorPage: status 50x</div>
    </div>
  );
};

export default ServerErrorPage;
