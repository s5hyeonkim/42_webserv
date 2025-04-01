import { Outlet } from "react-router-dom";

const ErrorPage = () => {
  console.log("default error page");

  return (
    <div>
      <Outlet />
      <div>ErrorPage</div>
    </div>
  );
};

export default ErrorPage;
