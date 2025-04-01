import { Outlet } from "react-router-dom";

const ClientErrorPage = () => {
  console.log("client error page");

  return (
    <div>
      <Outlet />
      <div>ErrorPage: status 40x</div>
    </div>
  );
};

export default ClientErrorPage;
